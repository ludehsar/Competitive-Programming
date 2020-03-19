@echo off
echo Before proceeding further, you will need to install nodejs and latex support in your PC.
where notebook-generator > nul
if %ERRORLEVEL% GEQ 1 (npm install -g notebook-generator) else (echo Notebook generator is already installed, proceeding further)
set /p team="Enter your team name: "
set /p university="Enter your university name: "
call notebook-generator ./ --author "%team% - %university%" --initials "%university% (%team%)" --size 8 --columns 3 --paper a4paper
pause