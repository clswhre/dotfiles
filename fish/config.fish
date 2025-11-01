source /usr/share/cachyos-fish-config/cachyos-config.fish

# overwrite greeting
# potentially disabling fastfetch
#function fish_greeting
#    # smth smth
#end

fish_add_path /home/clswhre/.spicetify

function ls --wraps='eza -al --color=always --group-directories-first --icons --no-permissions --no-user' --description 'alias ls=eza (long, no perms, no user)'
    eza -al --color=always --group-directories-first --icons --no-permissions --no-user $argv
end
