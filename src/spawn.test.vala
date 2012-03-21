public class Spawn {

uint timeout;
string progname;
string output;
Pid pid;
int status;
int outfd;
int errfd;
IOChannel outchan;
IOChannel errchan;
MainLoop loop;

public
Spawn(string name)
{
	progname = name;
}

void
on_async_exit(Pid pid, int exit_status)
{
	Source.remove(timeout);
	Process.close_pid(pid);
	status = exit_status;
	loop.quit();
}

bool
on_output(IOChannel source, IOCondition cond)
{
	if (cond == IOCondition.HUP) return false;

	try {
		int fd = source.unix_get_fd();
		source.read_line(out output, null, null);
		if (fd == outfd)
			stdout.printf("%s", output);
		if (fd == errfd)
			stdout.printf("%c[1m%c[31m%s%c[0m",
			    (char)27, (char)27, output, (char)27);
	} catch (ConvertError err) {
		stderr.printf("Conversion error!: %s\n", err.message);
		return false;
	} catch (IOChannelError err) {
		stderr.printf("Read error!: %s\n", err.message);
		return false;
	}
	return true;
}

public void
execute(ref string[] argv)
{
	bool rv;

	try {
		loop = new MainLoop(null, false);
		rv = Process.spawn_async_with_pipes(null, argv, null,
			SpawnFlags.DO_NOT_REAP_CHILD | SpawnFlags.SEARCH_PATH,
			null, out pid, null, out outfd, out errfd);
		if(!rv) {
			stderr.printf("%s\n", "SPAWN FAILED");
			return;
		}
	} catch (SpawnError error) {
		stderr.printf("SpawnError: %s\n", error.message);
		return;
	}

	ChildWatch.add(pid, on_async_exit);

	outchan = new IOChannel.unix_new(outfd);
	errchan = new IOChannel.unix_new(errfd);
	outchan.add_watch(IOCondition.IN | IOCondition.HUP, on_output);
	errchan.add_watch(IOCondition.IN | IOCondition.HUP, on_output);

	timeout = Timeout.add(250, () => {
		stdout.printf("Process timed out.\n");
		on_async_exit(pid, 1);
		return true;
	});
	loop.run();
}

} /* class Spawn */
/*
int
main(string[] argv)
{
	string[] cmd = new string[argv.length];
	for (int i = 0; i < cmd.length; i++) {
		if (i == cmd.length-1) continue;
		cmd[i] = argv[i+1];
	}
	cmd[cmd.length-1] = null;
	var spawn = new Spawn(cmd[0]);
	spawn.execute(ref cmd);
	return 0;
}*/
