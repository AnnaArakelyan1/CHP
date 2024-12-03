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

# Read the encrypted content as a string
$encryptedContent = Get-Content -Path $filePath -Raw

# Decrypt the content by shifting each character in the printable range (32–126)
$decryptedContent = ($encryptedContent.ToCharArray() | ForEach-Object {
    $ascii = [int][char]$_
    if ($ascii -ge 32 -and $ascii -le 126) {
        $newAscii = (($ascii - 32 - $shift + 95) % 95) + 32
        [char]$newAscii
    } else {
        $_  # Keep non-printable characters unchanged
    }
}) -join ""  # Join the decrypted characters into a single string

# Save the decrypted content to a new file
$decryptedFilePath = "$filePath.decrypted"
Set-Content -Path $decryptedFilePath -Value $decryptedContent

Write-Host "Decrypted file created at: $decryptedFilePath"
