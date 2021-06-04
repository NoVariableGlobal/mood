# Version: 7

param (
	[switch] $Clean,

	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration = @("Debug", "Release"),

	# Dependencies
	[bool] $BuildDependencies = $true,

	# Project
	[bool] $BuildProject = $true
)

$ErrorActionPreference = "Stop"

If ($Clean)
{
	& "$PSScriptRoot/clean.ps1"
}

if ($BuildDependencies)
{
	$local:RootDirectory = Split-Path $PSScriptRoot -Parent
	$local:OutputDirectory = Join-Path -Path $RootDirectory -ChildPath "bin"
	& "$RootDirectory/deps/one-thousand-years/scripts/build.ps1" -Configuration $Configuration -OutputDirectory $OutputDirectory
}

if ($BuildProject)
{
	& "$PSScriptRoot/build-project.ps1" -Configuration $Configuration
}

exit $LastExitCode
