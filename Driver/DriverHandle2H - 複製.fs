
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
@WRITE_STR"typedef VOID (FUNPTR)();";
@WRITE_STR"\n\n";
@WRITE_STR"FUNPTR * BeforeTaskSwitchHookList[] = {\n";
@WRITE_STR@S_ARG1;
@WRITE_STR"\n};\n\n";

@WRITE_STR"FUNPTR * RootTaskInitHookList[] = {\n";
@WRITE_STR@S_ARG2;
@WRITE_STR"\n};";

@WRITE_STR"\n\n#endif";