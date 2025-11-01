function ls --wraps='eza -al --color=always --group-directories-first --icons' --wraps='eza -al --color=always --group-directories-first --icons --no-permissions --no-user' --description 'alias ls=eza (long, no perms, no user)'
    eza -al --color=always --group-directories-first --icons --no-permissions --no-user $argv
end
