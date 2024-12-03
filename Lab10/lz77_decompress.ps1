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
$compressedContent = Get-Content -Path $filePath -Raw

# Initialize variables for decompression
$decompressedData = ""
$currentPos = 0
$contentLength = $compressedContent.Length

while ($currentPos -lt $contentLength) {
    # Check if we're at a character followed by [offset|length]
    if ($currentPos + 1 -lt $contentLength -and $compressedContent[$currentPos + 1] -eq '[') {
        $charBeforeBracket = $compressedContent[$currentPos]
        
        # Find the closing bracket
        $bracketEndPos = $compressedContent.IndexOf(']', $currentPos)
        if ($bracketEndPos -eq -1) {
            Write-Host "Error: Invalid compressed format - missing closing bracket"
            exit 1
        }
        
        # Extract the offset and length values
        $compressedSequence = $compressedContent.Substring($currentPos + 2, $bracketEndPos - ($currentPos + 2))
        $values = $compressedSequence.Split('|')
        
        if ($values.Length -ne 2) {
            Write-Host "Error: Invalid compressed format - expected offset|length"
            exit 1
        }
        
        try {
            $offset = [int]$values[0]
            $length = [int]$values[1]
            
            # Calculate the start position in the decompressed data
            $startPos = $decompressedData.Length - $offset
            
            # Copy the matched sequence
            for ($i = 0; $i -lt $length - 1; $i++) {
                $decompressedData += $decompressedData[$startPos + $i]
            }
            # Add the character before the bracket as the last character
            $decompressedData += $charBeforeBracket
            
            # Move the position past the closing bracket
            $currentPos = $bracketEndPos + 1
            
        } catch {
            Write-Host "Error: Invalid number format in compressed sequence"
            exit 1
        }
    } else {
        # Copy uncompressed character
        $decompressedData += $compressedContent[$currentPos]
        $currentPos++
    }
}

# Write the decompressed data back to the file
try {
    Set-Content -Path $filePath -Value $decompressedData -NoNewline
    Write-Host "Decompression complete. Decompressed data written back to the original file."
} catch {
    Write-Host "Error writing to file: $_"
    exit 1
}
