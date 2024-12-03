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
$content = Get-Content -Path $filePath -Raw
$windowSize = 64  # Maximum size of the sliding window
$matchSize = 15   # Maximum length of a match

$compressedData = ""
$currentPos = 0
$contentLength = $content.Length

while ($currentPos -lt $contentLength) {
    $bestMatchLength = 0
    $bestMatchOffset = 0

    # Define the start of the search window
    $searchStart = [Math]::Max(0, $currentPos - $windowSize)

    for ($i = $searchStart; $i -lt $currentPos; $i++) {
        $matchLen = 0
        while (
            $matchLen -lt $matchSize -and
            ($currentPos + $matchLen) -lt $contentLength -and
            $content[$i + $matchLen] -eq $content[$currentPos + $matchLen]
        ) {
            $matchLen++
        }

        if ($matchLen -gt $bestMatchLength) {
            $bestMatchLength = $matchLen
            $bestMatchOffset = $currentPos - $i
        }
    }

    # Get the next character after the match
    $followingChar = if (($currentPos + $bestMatchLength) -lt $contentLength) { $content[$currentPos + $bestMatchLength] } else { '' }

    if ($bestMatchLength -gt 1) {
        # Append the match as [offset|length] and the following character
        $compressedData += "$($content[$currentPos + $bestMatchLength - 1])[$bestMatchOffset|$bestMatchLength]"
    } else {
        # No match found, append the current character as is
        $compressedData += $content[$currentPos]
    }

    $currentPos += [Math]::Max($bestMatchLength, 1)
}

# Overwrite the original file with the compressed data
Set-Content -Path $filePath -Value $compressedData
Write-Host "Compression complete. Compressed data written back to the original file."
