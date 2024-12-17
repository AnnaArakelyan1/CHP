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

REM Set the output directory
set output_dir=C:\Users\HP\OneDrive\Documents\chp

REM Ensure the directory exists
if not exist "%output_dir%" (
    echo Directory %output_dir% does not exist. Creating it now...
    mkdir "%output_dir%"
)

REM Check if the input is a file or text
if exist "%input%" (
    REM If the input is a file, process it
    REM Extract the file name and extension from the full path
    for %%f in ("%input%") do set filename=%%~nxf

    REM Define output file path for the hash values
    set md5_file=%output_dir%\MD5-%filename%.txt
    set sha1_file=%output_dir%\SHA1-%filename%.txt
    set sha256_file=%output_dir%\SHA256-%filename%.txt

    REM Calculate and save hashes for the file using certutil
    echo Calculating MD5 hash for %input%
    certutil -hashfile "%input%" MD5 | findstr /r /v "^$" | findstr /v "certutil" > "%md5_file%"
    echo MD5 Hash saved to %md5_file%

    echo Calculating SHA1 hash for %input%
    certutil -hashfile "%input%" SHA1 | findstr /r /v "^$" | findstr /v "certutil" > "%sha1_file%"
    echo SHA1 Hash saved to %sha1_file%

    echo Calculating SHA256 hash for %input%
    certutil -hashfile "%input%" SHA256 | findstr /r /v "^$" | findstr /v "certutil" > "%sha256_file%"
    echo SHA256 Hash saved to %sha256_file%

) else (
    REM If the input is not a file, treat it as text input
    echo Hashing text input using PowerShell...

    REM Define output file path for the text hashes
    set md5_file=%output_dir%\MD5-text-hash.txt
    set sha1_file=%output_dir%\SHA1-text-hash.txt
    set sha256_file=%output_dir%\SHA256-text-hash.txt

    REM Calculate and save MD5 hash for text input
    powershell -Command "$input='%input%'; $bytes=[System.Text.Encoding]::UTF8.GetBytes($input); $md5=[BitConverter]::ToString((New-Object Security.Cryptography.MD5CryptoServiceProvider).ComputeHash($bytes)); $md5 -replace '-',''" > "%md5_file%"
    echo MD5 Hash saved to %md5_file%

    REM Calculate and save SHA1 hash for text input
    powershell -Command "$input='%input%'; $bytes=[System.Text.Encoding]::UTF8.GetBytes($input); $sha1=[BitConverter]::ToString((New-Object Security.Cryptography.SHA1Managed).ComputeHash($bytes)); $sha1 -replace '-',''" > "%sha1_file%"
    echo SHA1 Hash saved to %sha1_file%

    REM Calculate and save SHA256 hash for text input
    powershell -Command "$input='%input%'; $bytes=[System.Text.Encoding]::UTF8.GetBytes($input); $sha256=[BitConverter]::ToString((New-Object Security.Cryptography.SHA256Managed).ComputeHash($bytes)); $sha256 -replace '-',''" > "%sha256_file%"
    echo SHA256 Hash saved to %sha256_file%

)

pause
goto menu



:exit
echo Exiting... Goodbye!
exit
