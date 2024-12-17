@echo off
:menu
echo ===================================
echo       Windows Utility Menu
echo ===================================
echo 1. Get IP Address
echo 2. Make Traceroute
echo 3. Resolve DNS Name
echo 4. Encrypt Text (Caesar)
echo 5. Decrypt Text (Caesar)
echo 6. Encrypt File (Caesar)
echo 7. Decrypt File (Caesar)
echo 8. Compress File (LZ77)
echo 9. Decompress File (LZ77)
echo 10. Calculate Hash Value
echo 11. Exit
echo ===================================
set /p choice="Select an option: "

if "%choice%"=="1" goto get_ip
if "%choice%"=="2" goto traceroute
if "%choice%"=="3" goto resolve_dns
if "%choice%"=="4" goto encrypt_text
if "%choice%"=="5" goto decrypt_text
if "%choice%"=="6" goto encrypt_file
if "%choice%"=="7" goto decrypt_file
if "%choice%"=="8" goto compress_file
if "%choice%"=="9" goto decompress_file
if "%choice%"=="10" goto hash_value
if "%choice%"=="11" exit
goto menu

:get_ip
ipconfig | findstr "IPv4"
ipconfig | findstr "IPv6"
pause
goto menu

:traceroute
set /p target="Enter the hostname or IP address: "
tracert %target%
pause
goto menu

:resolve_dns
set /p dns_name="Enter the DNS name: "
nslookup %dns_name%
pause
goto menu

:encrypt_text
set /p text="Enter text to encrypt: "
set /p shift="Enter shift value: "
echo Encrypting text: %text% with shift value: %shift%
powershell -ExecutionPolicy Bypass -File "C:\Users\HP\OneDrive\Documents\chp\caesar_cipher_encrypt.ps1" -text "%text%" -shift %shift%
pause
goto menu


:decrypt_text
set /p text="Enter text to decrypt: "
set /p shift="Enter shift value used for encryption: "
echo Decrypting text: %text% with shift value: %shift%
powershell -ExecutionPolicy Bypass -File "C:\Users\HP\OneDrive\Documents\chp\caesar_cipher_decrypt.ps1" -text "%text%" -shift %shift%
pause
goto menu




:encrypt_file
set /p file="Enter the file path to encrypt: "
set "scriptPath=C:\Users\HP\OneDrive\Documents\chp\file_caesar_cipher.ps1"

echo Checking if script exists at %scriptPath%...
if not exist "%scriptPath%" (
    echo Error: The script '%scriptPath%' does not exist.
    echo Make sure the script is located at the specified path.
    pause
    goto menu
)

echo Script found. Proceeding with encryption...
powershell -ExecutionPolicy Bypass -File "%scriptPath%" -filePath "%file%" -shift 3
echo File encrypted successfully.
pause
goto menu


:decrypt_file
set /p file="Enter the file path to decrypt: "
set /p shift="Enter shift value used for encryption: "
set "scriptPath=C:\Users\HP\OneDrive\Documents\chp\file_caesar_cipher_decrypt.ps1"
if not exist "%scriptPath%" (
    echo Error: The script '%scriptPath%' does not exist.
    pause
    goto menu
)

if not exist "%file%" (
    echo Error: The file '%file%' does not exist.
    pause
    goto menu
)

echo Decrypting file...
powershell -ExecutionPolicy Bypass -File "%scriptPath%" -filePath "%file%" -shift %shift%
echo File decrypted successfully.
pause
goto menu



:compress_file
set /p file="Enter the file path to compress: "
echo File path provided: "%file%"  REM Debugging line to check for spaces or issues in the path
set "scriptPath=C:\Users\HP\OneDrive\Documents\chp\lz77_compress.ps1"

if not exist "%scriptPath%" (
    echo Error: The script '%scriptPath%' does not exist.
    pause
    goto menu
)

if not exist "%file%" (
    echo Error: The file '%file%' does not exist.
    pause
    goto menu
)

echo File path is valid. Proceeding with compression...
powershell -ExecutionPolicy Bypass -File "%scriptPath%" -filePath "%file%"
echo File compressed successfully.
pause
goto menu



:decompress_file
set /p file="Enter the file path to decompress: "
powershell -ExecutionPolicy Bypass -File "C:\Users\HP\OneDrive\Documents\chp\lz77_decompress.ps1" -filePath "%file%"
echo File decompressed successfully.
pause
goto menu

:hash_value
set /p input="Enter text or file path: "
echo Calculating hashes...

REM Check if input is a file or a string
if exist "%input%" (
    REM Extract the file name and extension from the full path
    for %%f in ("%input%") do set filename=%%~nxf

    REM Calculate and print hashes for the file using certutil
    echo MD5 Hash:
    certutil -hashfile "%input%" MD5 | findstr /r /v "^$" | findstr /v "certutil"

    echo SHA256 Hash:
    certutil -hashfile "%input%" SHA256 | findstr /r /v "^$" | findstr /v "certutil"

    echo Default Hash:
    certutil -hashfile "%input%" | findstr /r /v "^$" | findstr /v "certutil"
) else (
    REM If the input is not a file, treat it as a text input and hash it
    echo Hashing text input using PowerShell...

    REM Escape the input and hash it using PowerShell
    powershell -Command "$input='%input%'; $bytes=[System.Text.Encoding]::UTF8.GetBytes($input); $hash=[BitConverter]::ToString((New-Object Security.Cryptography.SHA256Managed).ComputeHash($bytes)); $hash -replace '-',''"

    pause
)

goto menu





:exit
echo Exiting... Goodbye!
exit
