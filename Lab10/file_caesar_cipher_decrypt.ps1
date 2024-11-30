param (
    [string]$filePath,
    [int]$shift
)

# Trim any leading/trailing spaces from the file path
$filePath = $filePath.Trim()

# Verify that the file exists
if (!(Test-Path -Path $filePath)) {
    Write-Host "Error: The file path '$filePath' does not exist."
    exit
}

# Read the encrypted content as a byte array
$encryptedContent = [System.IO.File]::ReadAllBytes($filePath)

# Decrypt the content by shifting each byte value back
$decryptedContent = $encryptedContent | ForEach-Object {
    ($_ - $shift + 256) % 256
}

# Save the decrypted content to a new file
$decryptedFilePath = "$filePath.decrypted"
[System.IO.File]::WriteAllBytes($decryptedFilePath, [byte[]]$decryptedContent)

Write-Host "Decrypted file created at: $decryptedFilePath"
