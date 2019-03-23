@LOOP_READLINE!=NULL {
    @S_ARG0 = @LINE;
    @IF(!@S_ARG0.@CONTAIN("#")) {
        @IF(@S_ARG0.@CONTAIN("VALUE")) {
            @S_ARG0.@TRIM(' ');
            @S_ARG0.@SPLIT('=',1);
            @S_ARG1 = @S_ARG0;
        }
        @S_ARG0 = @LINE;
        @IF(@S_ARG0.@CONTAIN("ENTRY")) {
            @S_ARG0.@TRIM(' ');
            @S_ARG0.@SPLIT('=',1);
            @S_ARG2 = @S_ARG0;

            @WRITE_STR"%PROJECT_DIR%\BuildTool\FileScript.exe ";

            @WRITE_STR"%PROJECT_DIR%\BuildTool\ScanFileList.fs ";

            @WRITE_STR"%PROJECT_DIR%\Build\BuildFile.txt ";

            @WRITE_STR"%PROJECT_DIR%\Build\BuildFile.txt ";

            @WRITE_STR"%PROJECT_DIR%";
            @WRITE_STR@S_ARG1;
            @WRITE_STR"\\";
            @WRITE_STR@S_ARG2;
            @WRITE_STR".cif ";
            @WRITE_STR"\n";
        }
    }
}

@WRITE_STR"%PROJECT_DIR%\BuildTool\FileScript.exe %PROJECT_DIR%\BuildTool\MakeMakP1.fs %PROJECT_DIR%\BuildTool\DosMakP1.txt %PROJECT_DIR%\Build\123.txt %PROJECT_DIR%\Build\BuildFile.txt\n";
@WRITE_STR"%PROJECT_DIR%\BuildTool\FileScript.exe %PROJECT_DIR%\BuildTool\MakeMakP2.fs %PROJECT_DIR%\Build\123.txt %PROJECT_DIR%\Build\123.txt %PROJECT_DIR%\BuildTool\DosMakP2.txt\n";

@WRITE_STR"%PROJECT_DIR%\BuildTool\FileScript.exe %PROJECT_DIR%\BuildTool\MakeMakP3.fs %PROJECT_DIR%\Build\123.txt %PROJECT_DIR%\Build\123.txt %PROJECT_DIR%\Build\BuildFile.txt %PROJECT_DIR%\BuildTool\DosMakP3.txt\n";
@WRITE_STR"%PROJECT_DIR%\BuildTool\FileScript.exe %PROJECT_DIR%\Driver\DriverHandle2H.fs %PROJECT_DIR%\Driver\driver.sdl %PROJECT_DIR%\Include\Build\driverHandleList.h\n";
@WRITE_STR"%PROJECT_DIR%\BuildTool\Compiler\AMD64\\nmake.exe -f %PROJECT_DIR%\Dos.mak all";