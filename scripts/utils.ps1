param(
    [switch] $Interactive,
    [switch] $Init,
    [switch] $Update,
    [switch] $Upgrade,
    [switch] $Format,
    [switch] $Build,
    [switch] $Release,
    [string[]] $ReleaseArguments
)

$ErrorActionPreference = "Stop"

$local:ProjectName = "MOOD"
$local:EngineName = "One Thousand Years"
$local:RootFolder = Split-Path $PSScriptRoot -Parent

function Read-Boolean {
    [OutputType([bool])]
    param (
        [string] $Message
    )

    $private:value = Read-Host -Prompt "$Message [y/n]"
    Switch -regex ($value.ToLower()) {
        "y(es?|eah?)?" { Return $True }
        "n(o|ah?)?" { Return $False }
        Default { Return Read-Boolean -Message $Message }
    }
}

If ($Interactive) {
    If (!$Init.IsPresent) {
        $Init = Read-Boolean -Message "Initialize $ProjectName's sub-modules"
    }

    If (!$Update.IsPresent) {
        $Update = Read-Boolean -Message "Update $ProjectName's sub-modules"
    }

    If (!$Upgrade.IsPresent) {
        $Upgrade = Read-Boolean -Message "Upgrade $EngineName to its latest commit"
    }

    If (!$Format.IsPresent) {
        $Format = Read-Boolean -Message "Format all of $ProjectName's source files"
    }

    If (!$Build.IsPresent) {
        $Build = Read-Boolean -Message "Build all dependencies and $ProjectName"
    }

    If (!$Release.IsPresent) {
        $Release = Read-Boolean -Message "Generate a release ZIP for $ProjectName"
    }
}

If ($Init) {
    # Prints information about the step being taken
    Write-Host "Initializing submodules for " -ForegroundColor Blue -NoNewline
    Write-Host $ProjectName                   -ForegroundColor Cyan -NoNewline
    Write-Host "... "                         -ForegroundColor Blue

    # Run the process
    $private:duration = Measure-Command {
        Push-Location $RootFolder
        & git submodule init
        Pop-Location
    }

    # Print information to the screen
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished in "       -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                    -ForegroundColor Green
    } Else {
        Write-Host "# Errored with code $LastExitCode in " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)                  -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                     -ForegroundColor Red
        Throw "Failed to initialize the submodule.";
    }
}

If ($Update) {
    # Prints information about the step being taken
    Write-Host "Updating submodules for " -ForegroundColor Blue -NoNewline
    Write-Host $ProjectName               -ForegroundColor Cyan -NoNewline
    Write-Host "... "                     -ForegroundColor Blue

    # Run the process
    $private:duration = Measure-Command {
        Push-Location $RootFolder
        & git submodule update
        Pop-Location
    }

    # Print information to the screen
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished in "       -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                    -ForegroundColor Green
    } Else {
        Write-Host "# Errored with code $LastExitCode in " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)                  -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                     -ForegroundColor Red
        Throw "Failed to update the submodules.";
    }
}

If ($Upgrade) {
    # Prints information about the step being taken
    Write-Host "Upgrading "            -ForegroundColor Blue -NoNewline
    Write-Host $EngineName             -ForegroundColor Cyan -NoNewline
    Write-Host " to latest version... " -ForegroundColor Blue

    # Run the process
    $private:duration = Measure-Command {
        # Enter the engine's repository, then run fetch and pull
        Push-Location "$RootFolder\deps\one-thousand-years"
        & git pull origin master
        Pop-Location

        # Add submodule's changes to the git stage
        Push-Location $RootFolder
        & git add "$RootFolder\deps\one-thousand-years"
        Pop-Location
    }

    # Print information to the screen
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished in "       -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                    -ForegroundColor Green
    }
    Else {
        Write-Host "# Errored with code $LastExitCode in " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)                  -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                     -ForegroundColor Red
        Throw "Failed to upgrade the engine.";
    }

    # If the engine was updated and added to stage, scan the build.ps1 file and replace
    # it's version number. Why? This is done because CI has a hash-keyed cache that
    # depends on said file. By bumping this little number, the hash changes, and thus the
    # old cache will be invalidated and discarded in the next runs, avoiding caching
    # issues where PRs that update the engine get failing build in CI despite of working
    # perfectly locally.
    If ($(git status -s).Contains('M  deps/one-thousand-years')) {
        Write-Host "Updating build for CI re-hash... " -ForegroundColor Green -NoNewline

        $local:buildPath = "$RootFolder\scripts\build.ps1"
        $local:read = Get-Content -Path $buildPath
        $local:version = $null
        $read | ForEach-Object {
            if ($_.ReadCount -eq 1) {
                # Parse the version
                $version = [int]$_.Split(" ")[-1]

                # Write the new version
                $_ -Replace '.+', "# Version $($version + 1)"
            }
            else {
                # Keep the original content
                $_
            }
        } | Set-Content $buildPath

        If ($null -eq $version) {
            Write-Host "Could not find the file version." -ForegroundColor Red
        }
        Else {
            Write-Host "Version "                 -ForegroundColor Green -NoNewline
            Write-Host $version                   -ForegroundColor Cyan  -NoNewline
            Write-Host " -> "                     -ForegroundColor Green -NoNewline
            Write-Host $($version + 1)            -ForegroundColor Cyan  -NoNewline
            Write-Host ". Adding it to stage... " -ForegroundColor Green -NoNewline

            # Run the process
            $private:duration = Measure-Command {
                # Add script's changes to the git stage
                & git add $buildPath
            }

            # Print information to the screen
            If ($LastExitCode -Eq 0) {
                Write-Host "Finished in "         -ForegroundColor Green -NoNewLine
                Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
                Write-Host "."                    -ForegroundColor Green
            }
            Else {
                Write-Host "Errored with code $LastExitCode in " -ForegroundColor Red  -NoNewLine
                Write-Host ("{0:g}" -f $duration)                -ForegroundColor Cyan -NoNewLine
                Write-Host "."                                   -ForegroundColor Red
                Throw "Failed to add the build to stage.";
            }
        }
    }
}

If ($Format) {
    # Prints information about the step being taken
    Write-Host "Formatting " -ForegroundColor Blue -NoNewline
    Write-Host $ProjectName  -ForegroundColor Cyan -NoNewline
    Write-Host "... "        -ForegroundColor Blue

    # Run the process
    $private:duration = Measure-Command {
        & "$RootFolder\scripts\format.ps1"
    }

    # Print information to the screen
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished in "       -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                    -ForegroundColor Green
    } Else {
        Write-Host "# Errored with code $LastExitCode in " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)                  -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                     -ForegroundColor Red
        Throw "Failed to format the project.";
    }
}

If ($Build) {
    # Prints information about the step being taken
    Write-Host "Building "  -ForegroundColor Blue -NoNewline
    Write-Host $ProjectName -ForegroundColor Cyan -NoNewline
    Write-Host "... "       -ForegroundColor Blue

    # Run the process
    $private:startTime = Get-Date
    & "$RootFolder\scripts\build.ps1"
    $private:exitTime = Get-Date

    # Print information to the screen
    $private:duration = $exitTime - $startTime
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished in "       -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                    -ForegroundColor Green
    } Else {
        Write-Host "# Errored with code $LastExitCode in " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)                  -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                     -ForegroundColor Red
        Throw "Failed to build the project.";
    }
}

If ($Release) {
    # Prints information about the step being taken
    Write-Host "Releasing " -ForegroundColor Blue -NoNewline
    Write-Host $ProjectName -ForegroundColor Cyan -NoNewline
    Write-Host "... "       -ForegroundColor Blue

    # Run the process
    $private:startTime = Get-Date
    & "$RootFolder\scripts\release.ps1" $ReleaseArguments
    $private:exitTime = Get-Date

    # Print information to the screen
    $private:duration = $exitTime - $startTime
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished in "       -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                    -ForegroundColor Green
    } Else {
        Write-Host "# Errored with code $LastExitCode in " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)                  -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                     -ForegroundColor Red
        Throw "Failed to release the project.";
    }
}
