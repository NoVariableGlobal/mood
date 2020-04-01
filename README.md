# MOOD

MOOD is a shooter game inspired by [DOOM] and [Dead Ops Arcade].

## Set-Up

There are two ways to set-up, we provide a [PowerShell] script to make things easier, but you can also set up everything
manually if you prefer or if the automated script gives you problems (please open an issue or contact the team if this
happens!).

In advance, we require you to have installed [CMake] and [Visual Studio 2019][VisualStudio2019].

### Automated Set-Up

First of all, you might need to change [PowerShell]'s policy settings to run our script, it is because we provide an
unofficial script, to allow it, you will need to use the [Set-ExecutionPolicy] command, you can safely do the following:

```ps1
Set-ExecutionPolicy Unrestricted -Scope Process
```

> The `-Scope Process` sets the execution policy for the [PowerShell]'s session, meaning it will reset to default once
you close the window. If you drop it, `Scope`'s value will be `LocalMachine`, affecting all users of the computer.

To run the script, we will use an existing [PowerShell] window, you can open it by pressing `Shift` and then do right
click anywhere in the project's folder, it will show you some extra options, including `Open PowerShell window here`.
Alternatively, open a new window and `cd` to the project's folder.

Once you have your [PowerShell] window in this project's folder, you can use our interactive utilities script to
simplify the entire set-up:

```ps1
.\scripts\utils.ps1 -Interactive
```

Alternatively, you can run the following command to set up all dependencies and compile the project:

```ps1
.\scripts\build.ps1
```

That's all!

### Manual Set-Up

All the steps will be done with [CMake]'s GUI and [VS2019][VisualStudio2019], you are welcome to use scripts in the
shell of your preference.

#### Engine

Please refer to [One Thousand Years]'s documentation and follow all the steps [here][oty-manual-setup]

> If you encountered any issues, please open an issue including the steps taken and the warnings or errors you
encountered. If you found no problem so far, you should be able to compile this project without problems.

## Contributing

1. Fork it!
1. Create your feature branch: `git checkout -b my-new-feature`
1. Commit your changes: `git commit -am 'Add some feature'`
1. Push to the branch: `git push origin my-new-feature`
1. Submit a pull request!

## Author

**MOOD** © [NoVariableGlobal][author], released under the
[MIT][license] License.
Authored and maintained by NoVariableGlobal.

> Github [NoVariableGlobal][author] - Twitter [@\_\_NVG\_\_][twitter]

[license]: https://github.com/NoVariableGlobal/mood/blob/master/LICENSE
[author]: https://github.com/NoVariableGlobal
[twitter]: https://twitter.com/__NVG__

[DOOM]: https://en.wikipedia.org/wiki/Doom_(franchise)
[Dead Ops Arcade]: https://callofduty.fandom.com/wiki/Dead_Ops_Arcade
[One Thousand Years]: https://github.com/NoVariableGlobal/global-engine
[PowerShell]: https://wikipedia.org/wiki/PowerShell
[Set-ExecutionPolicy]: https://docs.microsoft.com/powershell/module/microsoft.powershell.security/set-executionpolicy
[CMake]: https://cmake.org/
[VisualStudio2019]: https://visualstudio.microsoft.com/vs/
[oty-manual-setup]: https://github.com/NoVariableGlobal/global-engine#manual-set-up
