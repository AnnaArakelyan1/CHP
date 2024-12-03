param (
    [string]$text,
    [int]$shift
)

# Debug output to show the input text and shift value
Write-Host "Encrypting text: $text with shift value: $shift"

# Encrypt the input text by shifting characters forward within the ASCII range
$encryptedText = -join ($text.ToCharArray() | ForEach-Object {
    $asciiValue = [int][char]$_
    $shiftedValue = (($asciiValue + $shift) % 256)
    [char]$shiftedValue
})

# Output the encrypted text
Write-Output $encryptedText
