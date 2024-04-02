{ pkgs }: {
	deps = [
   pkgs.firefox
   pkgs.edit
   pkgs.nano
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}
