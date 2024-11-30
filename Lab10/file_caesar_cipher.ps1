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

# Read the content of the file as a byte array
$content = [System.IO.File]::ReadAllBytes($filePath)

# Encrypt the content by shifting each byte value
$encryptedContent = $content | ForEach-Object {
    ($_ + $shift) % 256
}

# Save the encrypted content to a new file
$encryptedFilePath = "$filePath.encrypted"
[System.IO.File]::WriteAllBytes($encryptedFilePath, [byte[]]$encryptedContent)

Write-Host "Encrypted file created at: $encryptedFilePath"
