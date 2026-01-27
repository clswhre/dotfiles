#!/bin/bash
set -e # Exit on error

# --- Configuration ---
DOTFILES_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
TIMESTAMP=$(date +%Y%m%d_%H%M%S)
BACKUP_ROOT="$HOME/.dotfiles_backup/$TIMESTAMP"
LOG_FILE="$DOTFILES_DIR/install_$TIMESTAMP.log"

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

# 1. Bulk Backup of .config
# ---------------------------------------------------------
log "Starting Backup Phase..."
mkdir -p "$BACKUP_ROOT"

if [ -d "$HOME/.config" ]; then
    log "Backing up entire ~/.config to $BACKUP_ROOT/config..."
    if command -v rsync &> /dev/null; then
        rsync -a "$HOME/.config/" "$BACKUP_ROOT/config/"
    else
        cp -r "$HOME/.config" "$BACKUP_ROOT/config"
    fi
else
    warn "$HOME/.config does not exist. Skipping backup."
fi

# 2. Installation Helper Function
# ---------------------------------------------------------
install_files() {
    local source_dir="$1"
    local target_dir="$2"
    
    if [ ! -d "$source_dir" ]; then
        # Silent return if optional folders (like .local/bin) don't exist in repo
        return
    fi

    mkdir -p "$target_dir"
    
    for item in "$source_dir"/*; do
        local name=$(basename "$item")
        local target="$target_dir/$name"

        # If target exists and is not a symlink, move it to backup
        if [ -e "$target" ] && [ ! -L "$target" ]; then
            log "Collision detected: $name. Moving original to backup."
            mv "$target" "$BACKUP_ROOT/${name}_collision"
        fi

        # Force create symlink
        ln -sf "$item" "$target"
        echo -e "${GREEN}[LINK]${NC} $item -> $target"
    done
}

# 3. Execution Phase
# ---------------------------------------------------------
log "Starting Installation Phase..."

# Install .config files
log "Installing .config files..."
install_files "$DOTFILES_DIR/.config" "$HOME/.config"

# Install .local files (binaries, scripts, etc)
log "Installing .local files..."
install_files "$DOTFILES_DIR/.local/bin" "$HOME/.local/bin"
install_files "$DOTFILES_DIR/.local/share" "$HOME/.local/share"

# Handle 'usr' folder - REMAPPING to .local/share
if [ -d "$DOTFILES_DIR/usr/share" ]; then
    log "Remapping usr/share to ~/.local/share..."
    install_files "$DOTFILES_DIR/usr/share" "$HOME/.local/share"
fi

log "Done. Backup stored in: $BACKUP_ROOT"
