param (
    [string]$text,
    [int]$shift
)

# Debug output to show the input text and shift value
Write-Host "Decrypting text: $text with shift value: $shift"

# Decrypt the input text by shifting characters back within the ASCII range
$decryptedText = -join ($text.ToCharArray() | ForEach-Object {
    $asciiValue = [int][char]$_
    $shiftedValue = (($asciiValue - $shift + 256) % 256)
    [char]$shiftedValue
})

# Output the decrypted text
Write-Output $decryptedText
