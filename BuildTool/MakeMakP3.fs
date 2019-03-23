//GARY : Frist write makefile part1 that in DosMakP1.txt
@LOOP_READLINE!=NULL{
	@WRITE_STR@LINE;
	@WRITE_STR"\n";
}

@SOURCE_F = @ARG3;
@LOOP_READLINE!=NULL{
	@S_ARG0 = @LINE;
	@S_ARG1 = @LINE;
	@S_ARG2 = @LINE;
	@IF(!@S_ARG0.@CONTAIN("ASMF")){
		@WRITE_STR"$(BUILD_DIR)\\";
		
		@S_ARG1.@SPLIT('\',1);
		@I_ARG2 = @SPLIT_COUNT;
		@I_ARG2 -= 1;
		@S_ARG2.@SPLIT('\',@I_ARG2);
		@S_ARG2.@REMOVE(".c");
		@WRITE_STR@S_ARG2;
		@WRITE_STR".obj: ";
		
		@WRITE_STR@S_ARG0;
		@WRITE_STR" $(HEADERS)";
		@WRITE_STR"\n	";
		@WRITE_STR"$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c ";
		@WRITE_STR@S_ARG0;
		@WRITE_STR" /Fo$(BUILD_DIR)\\";
		@WRITE_STR@S_ARG2;
		@WRITE_STR".obj";
		@WRITE_STR"\n";
	}
}

@LOOP_READLINE!=NULL{
	@S_ARG0 = @LINE;
	@S_ARG1 = @LINE;
	@S_ARG2 = @LINE;
	@IF(@S_ARG0.@CONTAIN("ASMF")){
		@WRITE_STR"$(BUILD_DIR)\\";
		
		@S_ARG1.@SPLIT('\',1);
		@I_ARG2 = @SPLIT_COUNT;
		@I_ARG2 -= 1;
		@S_ARG2.@SPLIT('\',@I_ARG2);
		@S_ARG2.@REMOVE(".asm");
		@WRITE_STR@S_ARG2;
		@WRITE_STR".obj: ";
		
		@S_ARG0.@REMOVE("ASMF\\");
		@WRITE_STR@S_ARG0;
		@WRITE_STR" $(HEADERS)";
		@WRITE_STR"\n	";
		@WRITE_STR"$(ASM) $(AFLAGS) $(INCLUDE) $(INCLUDE_H) /Fo$(BUILD_DIR)\\";
		@WRITE_STR@S_ARG2;
		@WRITE_STR".obj /c ";
		@WRITE_STR@S_ARG0;
		@WRITE_STR"\n";
	}
}

@WRITE_STR"\n";
@SOURCE_F = @ARG4;
@LOOP_READLINE!=NULL{
	@WRITE_STR@LINE;
	@WRITE_STR"\n";
}
