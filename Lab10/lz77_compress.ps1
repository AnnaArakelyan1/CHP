param (
    [Parameter(Mandatory=$true)]
    [string]$filePath
)

# Trim leading and trailing spaces from the path
$filePath = $filePath.Trim()
Write-Host "File path provided: '$filePath'"

# Check if the file exists
if (-Not (Test-Path $filePath)) {
    Write-Host "Error: The file '$filePath' does not exist."
    exit 1
}

# Read the content of the file
$content = Get-Content -Path $filePath -Raw

# Define compression parameters
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
    
    # Search for matches in the window
    for ($i = $searchStart; $i -lt $currentPos; $i++) {
        $matchLen = 0
        # Compare characters to find longest match
        while (
            $matchLen -lt $matchSize -and 
            ($currentPos + $matchLen) -lt $contentLength -and 
            ($i + $matchLen) -lt $currentPos -and
            $content[$i + $matchLen] -eq $content[$currentPos + $matchLen]
        ) {
            $matchLen++
        }
        
        if ($matchLen -gt $bestMatchLength) {
            $bestMatchLength = $matchLen
            $bestMatchOffset = $currentPos - $i
        }
    }
    
    # Get the following character if within bounds
    $followingChar = if (($currentPos + $bestMatchLength) -lt $contentLength) {
        $content[$currentPos + $bestMatchLength]
    } else {
        ''
    }
    
    if ($bestMatchLength -gt 1) {
        # Append the match as [offset|length] with the last matched character
        $compressedData += "$($content[$currentPos + $bestMatchLength - 1])[$bestMatchOffset|$bestMatchLength]"
        $currentPos += $bestMatchLength
    } else {
        # No match found, append the current character as is
        $compressedData += $content[$currentPos]
        $currentPos++
    }
}

# Write the compressed data back to the file
try {
    Set-Content -Path $filePath -Value $compressedData -NoNewline
    Write-Host "Compression complete. Compressed data written back to the original file."
} catch {
    Write-Host "Error writing to file: $_"
    exit 1
}
