@set PROJECT_DIR=%CD%
@set SDK_INSTALL_DIR=%PROJECT_DIR%\BuildTool\EFI_Toolkit_2.0
@set SDK_BUILD_ENV=em64t
@set PATH=%PROJECT_DIR%\BuildTool\Compiler\AMD64;%PATH%
@set PATH=%PROJECT_DIR%\BuildTool\Compiler\AMD64;%PATH%
@set PATH=%PROJECT_DIR%\BuildTool\Compiler\AMD64;%PATH%
@set PATH=%PROJECT_DIR%\BuildTool\Compiler\AMD64;%PATH%
@set PATH=%PROJECT_DIR%\BuildTool\Compiler\AMD64;%PATH%

rd IA64 /q /s
rd Build /q /s
rd Include\Build /q /s
del vc80.idb
del vc80.pdb
del Dragon.efi

IF NOT EXIST %PROJECT_DIR%\Include\Build (
	MD "%PROJECT_DIR%\Build\"
	MD "%PROJECT_DIR%\Include\Build\"
)

rem GARY: Creat a empty file for handle file list.
echo. 2>%PROJECT_DIR%\Build\BuildFile.txt
rem GARY: Step 1 => Scan all modules in folder and list that need to make in any modules.
%PROJECT_DIR%\BuildTool\FileScript.exe %PROJECT_DIR%\BuildTool\ScanBuildFolder.fs %PROJECT_DIR%\Dos.veb %PROJECT_DIR%\Build\BuildFolder.bat
rem GARY: Step 2 => Do any modules's bat file in folder to generate gloabl file list. 
%PROJECT_DIR%\Build\BuildFolder.bat

"%PROJECT_DIR%\BuildTool\Compiler\AMD64\nmake.exe" -f %PROJECT_DIR%\Dos.mak all