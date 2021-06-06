param (
	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration = @("Debug", "Release")
)

$ErrorActionPreference = "Stop"

$local:RootDirectory = Split-Path $PSScriptRoot -Parent
$local:OutputDirectory = Join-Path -Path $RootDirectory -ChildPath "bin"

& "$RootDirectory/deps/one-thousand-years/scripts/build.ps1" -Configuration $Configuration -OutputDirectory $OutputDirectory
