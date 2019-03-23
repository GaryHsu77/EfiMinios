//GARY : Frist write makefile part1 that in DosMakP1.txt
@LOOP_READLINE!=NULL{
	@WRITE_STR@LINE;
	@WRITE_STR"\n";
}

@WRITE_STR"\nFILES= \\";
@WRITE_STR"\n";
@SOURCE_F = @ARG3;
@I_ARG0 = 0;
@I_ARG1 = @SOURCE_F.@LINE_NUMBER;
@LOOP_READLINE!=NULL{
	@I_ARG0 += 1;
	@S_ARG0 = @LINE;
	@IF(!@S_ARG0.@CONTAIN("ASMF")){
		@WRITE_STR"	";
		@WRITE_STR@LINE;
		@IF(@I_ARG0!=@I_ARG1){
			@WRITE_STR"  \\";
			@WRITE_STR"\n";
		}
	}
	@IF(@S_ARG0.@CONTAIN("ASMF")){
		@I_ARG3 += 1;
	}
}
@I_ARG1 -= @I_ARG3;
@WRITE_STR"\n\n";

@WRITE_STR"ASMFILES= \\";
@WRITE_STR"\n";
@I_ARG0 = 0;
@LOOP_READLINE!=NULL{
	@S_ARG0 = @LINE;
	@IF(@S_ARG0.@CONTAIN("ASMF")){
		@I_ARG0 += 1;
		@S_ARG0.@REMOVE("ASMF\\");
		@WRITE_STR"	";
		@WRITE_STR@S_ARG0;
		@IF(@I_ARG0!=@I_ARG3){
			@WRITE_STR"  \\";
			@WRITE_STR"\n";
		}
	}
}
@WRITE_STR"\n\n";

@WRITE_STR"OBJS= \\";
@WRITE_STR"\n";
@I_ARG0 = 0;
@LOOP_READLINE!=NULL{
	@S_ARG0 = @LINE;
	@IF(!@S_ARG0.@CONTAIN("ASMF")){
		@I_ARG0 += 1;
		@S_ARG1 = @LINE;
		@S_ARG1.@SPLIT('\',1);
		@I_ARG2 = @SPLIT_COUNT;
		@I_ARG2 -= 1;
		@S_ARG0.@SPLIT('\',@I_ARG2);
		@WRITE_STR"	$(BUILD_DIR)\\";
		@S_ARG0.@REMOVE(".c");
		@WRITE_STR@S_ARG0;
		@WRITE_STR".obj";
		@IF(@I_ARG0!=@I_ARG1){
			@WRITE_STR"  \\";
			@WRITE_STR"\n";
		}
	}
}
@WRITE_STR"\n\n";

@WRITE_STR"ASMOBJS= \\";
@WRITE_STR"\n";
@I_ARG0 = 0;
@LOOP_READLINE!=NULL{
	@S_ARG0 = @LINE;
	@IF(@S_ARG0.@CONTAIN("ASMF")){
		@I_ARG0 += 1;
		@S_ARG1 = @LINE;
		@S_ARG1.@SPLIT('\',1);
		@I_ARG2 = @SPLIT_COUNT;
		@I_ARG2 -= 1;
		@S_ARG0.@SPLIT('\',@I_ARG2);
		@WRITE_STR"	$(BUILD_DIR)\\";
		@S_ARG0.@REMOVE(".asm");
		@WRITE_STR@S_ARG0;
		@WRITE_STR".obj";
		@IF(@I_ARG0!=@I_ARG3){
			@WRITE_STR"  \\";
			@WRITE_STR"\n";
		}
	}
}
@WRITE_STR"\n\n";