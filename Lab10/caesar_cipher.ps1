param (
    [string]$text,
    [int]$shift
)

function Encrypt-CaesarCipher {
    param (
        [string]$inputText,
        [int]$shiftValue
    )

    $result = ""
    foreach ($char in $inputText.ToCharArray()) {
        $asciiCode = [int][char]$char
        $encryptedAscii = ($asciiCode + $shiftValue) % 256
        $encryptedChar = [char]$encryptedAscii
        $result += $encryptedChar
    }
    return $result
}

# Encrypt and display the result
$encryptedText = Encrypt-CaesarCipher -inputText $text -shiftValue $shift
Write-Output $encryptedText
