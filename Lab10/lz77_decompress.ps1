param (
    [string]$filePath
)

# Trim leading and trailing spaces from the path
$filePath = $filePath.Trim()

Write-Host "File path provided: '$filePath'"  # Debugging line

# Check if the file exists
if (-Not (Test-Path $filePath)) {
    Write-Host "Error: The file '$filePath' does not exist."
    exit 1
}

# Read the content of the file
$compressedData = Get-Content -Path $filePath -Raw
$decompressedData = ""
$index = 0
$length = $compressedData.Length

while ($index -lt $length) {
    if ($compressedData[$index] -eq '[') {
        # Find the closing bracket to get the full [offset|length] part
        $closingBracketIndex = $compressedData.IndexOf(']', $index)
        $token = $compressedData.Substring($index + 1, $closingBracketIndex - $index - 1)
        $parts = $token -split '\|'

        $offset = [int]$parts[0]
        $matchLength = [int]$parts[1]
        
        # Get the following character after the match
        $nextChar = if (($closingBracketIndex + 1) -lt $length) { $compressedData[$closingBracketIndex + 1] } else { '' }

        # Add the substring based on offset and length
        $startOfMatch = $decompressedData.Length - $offset
        $match = $decompressedData.Substring($startOfMatch, $matchLength)
        $decompressedData += $match + $nextChar

        # Move the index past the token and the next character
        $index = $closingBracketIndex + 2
    } else {
        # Append a single character as is if not part of a token
        $decompressedData += $compressedData[$index]
        $index++
    }
}

# Save the decompressed data to an output file
$outputPath = "C:\Users\HP\OneDrive\Documents\chp\lz77_decompressed.txt"
Set-Content -Path $outputPath -Value $decompressedData
Write-Host "Decompression complete. Decompressed data written to $outputPath."
