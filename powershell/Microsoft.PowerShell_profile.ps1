oh-my-posh init pwsh --config "$env:POSH_THEMES_PATH\powerlevel10k_classic.omp.json" | Invoke-Expression

Import-Module posh-git
Import-Module PSReadLine

Set-Alias vi C:\Users\LENOVO\.local\bin\vi.ps1
Set-Alias lg lazygit

# Set Some Option for PSReadLine to show the history of our typed commands
Set-PSReadLineOption -PredictionSource History 
Set-PSReadLineOption -PredictionViewStyle ListView 
Set-PSReadLineOption -EditMode Windows 

#Fzf (Import the fuzzy finder and set a shortcut key to begin searching)
Import-Module PSFzf
Set-PsFzfOption -PSReadlineChordProvider 'Ctrl+f' -PSReadlineChordReverseHistory 'Ctrl+r'

$env:HTTP_PROXY="http://127.0.0.1:7890"
$env:HTTPS_PROXY="http://127.0.0.1:7890"

