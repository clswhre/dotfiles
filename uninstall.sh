#!/bin/bash
set -e

# --- Configuration ---
DOTFILES_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
LOG_FILE="$DOTFILES_DIR/uninstall.log"

# --- Colors ---
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

# --- Functions ---
log() {
    echo -e "${BLUE}[INFO]${NC} $1"
    echo "[INFO] $1" >> "$LOG_FILE"
}

warn() {
    echo -e "${RED}[WARN]${NC} $1"
    echo "[WARN] $1" >> "$LOG_FILE"
}

unlink_files() {
    local source_dir="$1"
    local target_dir="$2"

    if [ ! -d "$source_dir" ]; then
        return
    fi

    log "Cleaning up links in $target_dir..."

    for item in "$source_dir"/*; do
        local name=$(basename "$item")
        local target="$target_dir/$name"

        if [ -L "$target" ]; then
            local link_dest=$(readlink -f "$target")
            local repo_dest=$(readlink -f "$item")

            if [ "$link_dest" == "$repo_dest" ]; then
                rm "$target"
                echo -e "${GREEN}[REMOVED]${NC} $target"
            else
                warn "Skipping $target (Points to $link_dest, not this repo)"
            fi
        fi
    done
}

# --- Execution ---
log "Starting Uninstallation..."

unlink_files "$DOTFILES_DIR/.config" "$HOME/.config"
unlink_files "$DOTFILES_DIR/.local/bin" "$HOME/.local/bin"
unlink_files "$DOTFILES_DIR/.local/share" "$HOME/.local/share"

if [ -d "$DOTFILES_DIR/usr/share" ]; then
    unlink_files "$DOTFILES_DIR/usr/share" "$HOME/.local/share"
fi

echo ""
log "Uninstallation complete."
echo -e "${BLUE}NOTE:${NC} Backups are located in ${GREEN}$HOME/.dotfiles_backup/${NC}"
