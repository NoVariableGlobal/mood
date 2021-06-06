$local:RootDirectory = Split-Path $PSScriptRoot -Parent
$local:OutputDirectory = Join-Path -Path $RootDirectory -ChildPath "bin"

$local:DllFiles = Get-ChildItem -Path $OutputDirectory -Filter "*.dll";

Write-Host "# Now deleting " -ForegroundColor Blue -NoNewline
Write-Host $DllFiles.Length  -ForegroundColor Cyan -NoNewline
Write-Host " file(s) from '" -ForegroundColor Blue -NoNewline
Write-Host $OutputDirectory  -ForegroundColor Cyan -NoNewline
Write-Host "'... "           -ForegroundColor Blue -NoNewLine

if ($DllFiles.Length -ne 0) {
	$DllFiles | Remove-Item | Out-Null
	Write-Host "Finished!"           -ForegroundColor Green
} else {
	Write-Host "Skipped."            -ForegroundColor DarkGray
}

Remove-Variable DllFiles

& "$RootDirectory/deps/one-thousand-years/scripts/clean.ps1"
