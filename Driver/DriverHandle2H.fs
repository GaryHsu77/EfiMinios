
@WRITE_STR"#ifndef DRV_H\n";
@WRITE_STR"#define DRV_H\n";
@LOOP_READLINE!=NULL{
	@S_ARG0 = @LINE;
	@IF(@S_ARG0.@CONTAIN("BeforeOsTaskSwitchHook")){
		@S_ARG0 = @LINE;
		@S_ARG0.@SPLIT(':', 0);
		@S_ARG1 += @S_ARG0;
		@S_ARG1 += ",";
	}
	@S_ARG0 = @LINE;
	@IF(@S_ARG0.@CONTAIN("RootTaskInitHook")){
		@S_ARG0 = @LINE;
		@S_ARG0.@SPLIT(':', 0);
		@S_ARG2 += @S_ARG0;
		@S_ARG2 += ",";
	}
}
@WRITE_STR"\ntypedef VOID (FUNPTR)();\n\n";
@WRITE_STR"#define TaskSwitchHookList ";
@WRITE_STR@S_ARG1;
@WRITE_STR"\n";
@WRITE_STR"#define RootTaskInitList ";
@WRITE_STR@S_ARG2;
@WRITE_STR"\n\n";
@WRITE_STR"FUNPTR * BeforeTaskSwitchHookList[];";
@WRITE_STR"\n";
@WRITE_STR"FUNPTR * RootTaskInitHookList[];";

@WRITE_STR"\n\n#endif";