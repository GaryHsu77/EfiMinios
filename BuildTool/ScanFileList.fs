@LOOP_READLINE!=NULL{
	@WRITE_STR@LINE;
	@WRITE_STR"\n";
}

@SOURCE_F = @ARG3;

//@I_ARG0 = 0;
@LOOP_READLINE!=NULL{
	@S_ARG0 = @LINE;
	@IF(@S_ARG0.@CONTAIN("LOCATIOPN")){
		@S_ARG0.@TRIM(' ');
		@S_ARG0.@SPLIT('=',1);
		@S_ARG1 = @S_ARG0;
		@S_ARG1 += "\\";
	}
	
	@S_ARG0 = @LINE;
	@IF(@S_ARG0.@CONTAIN("FILE")){
		@S_ARG0.@TRIM(' ');
		@S_ARG0.@SPLIT('=',1);
		@WRITE_STR@S_ARG1;
		@WRITE_STR@S_ARG0;
		@WRITE_STR"\n";
		//@I_ARG0 += 1;
	}
	
	@S_ARG0 = @LINE;
	@IF(@S_ARG0.@CONTAIN("ASMF")){
		@S_ARG0.@TRIM(' ');
		@S_ARG0.@SPLIT('=',1);
		@WRITE_STR"ASMF\\";
		@WRITE_STR@S_ARG1;
		@WRITE_STR@S_ARG0;
		@WRITE_STR"\n";
		//@I_ARG0 += 1;
	}
}

//@WRITE_STR"FILE_LINE_COUNT=";
//@WRITE_STR@I_ARG0.@TO_STR;

