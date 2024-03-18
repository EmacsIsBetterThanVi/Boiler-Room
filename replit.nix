{ pkgs }: {
	deps = [
   pkgs.firefox
   pkgs.zulu
   pkgs.edit
   pkgs.unixtools.xxd
   pkgs.nano
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}
