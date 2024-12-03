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

# Read the file content as a single string
$content = Get-Content -Path $filePath -Raw

# Encrypt the content by shifting each character in the printable range (32–126)
$encryptedContent = ($content.ToCharArray() | ForEach-Object {
    $ascii = [int][char]$_
    if ($ascii -ge 32 -and $ascii -le 126) {
        $newAscii = (($ascii - 32 + $shift) % 95) + 32
        [char]$newAscii
    } else {
        $_  # Keep non-printable characters unchanged
    }
}) -join ""  # Join the encrypted characters into a single string

# Save the encrypted content to a new file
$encryptedFilePath = "$filePath.encrypted"
Set-Content -Path $encryptedFilePath -Value $encryptedContent

Write-Host "Encrypted file created at: $encryptedFilePath"
