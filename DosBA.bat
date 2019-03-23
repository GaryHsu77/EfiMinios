@set PROJECT_DIR=%CD%
@set SDK_INSTALL_DIR=%PROJECT_DIR%\BuildTool\EFI_Toolkit_2.0
@set SDK_BUILD_ENV=em64t
@set PATH=%PROJECT_DIR%\BuildTool\Compiler\AMD64;%PATH%
@set PATH=%PROJECT_DIR%\BuildTool\Compiler\AMD64;%PATH%
@set PATH=%PROJECT_DIR%\BuildTool\Compiler\AMD64;%PATH%
@set PATH=%PROJECT_DIR%\BuildTool\Compiler\AMD64;%PATH%
@set PATH=%PROJECT_DIR%\BuildTool\Compiler\AMD64;%PATH%
"%PROJECT_DIR%\BuildTool\Compiler\AMD64\nmake.exe" -f %PROJECT_DIR%\Dos.mak all
