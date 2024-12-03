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
powershell -ExecutionPolicy Bypass -File "C:\Users\HP\OneDrive\Documents\caesar_cipher.ps1" -text "%text%" -shift %shift% > encrypted_output.txt
for /f "usebackq delims=" %%A in (encrypted_output.txt) do set encrypted_text=%%A
echo Encrypted text is: %encrypted_text%
pause
goto menu

:decrypt_text
set /p text="Enter text to decrypt: "
set /p shift="Enter shift value used for encryption: "
set /a decrypt_shift=-%shift%
powershell -ExecutionPolicy Bypass -File "C:\Users\HP\OneDrive\Documents\caesar_cipher.ps1" -text "%text%" -shift %decrypt_shift% > decrypted_output.txt
for /f "usebackq delims=" %%A in (decrypted_output.txt) do set decrypted_text=%%A
echo Decrypted text is: %decrypted_text%
pause
goto menu

:encrypt_file
set /p file="Enter the file path to encrypt: "
set "scriptPath=C:\Users\HP\OneDrive\Documents\file_caesar_cipher.ps1"
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

powershell -File "%scriptPath%" -filePath "%file%"
echo File encrypted successfully.
pause
goto menu

:decrypt_file
set /p file="Enter the file path to decrypt: "
set /p shift="Enter shift value used for encryption: "
set "scriptPath=C:\Users\HP\OneDrive\Documents\file_caesar_cipher_decrypt.ps1"
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
certutil -hashfile "%input%" > def-hash-%input%.txt
certutil -hashfile "%input%" MD5 > MD5-%input%.txt
certutil -hashfile "%input%" SHA256 > SHA256-%input%.txt
echo Hash values saved to def-hash-%input%.txt, MD5-%input%.txt, and SHA256-%input%.txt.
pause
goto menu

:exit
echo Exiting... Goodbye!
exit
