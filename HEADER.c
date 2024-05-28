int address = 0;
while (header[address] != '\0') {
  char tokens[3][16] = {"", "", ""};
  int token_id = 0;
  int pointer = 0;
  while (header[address] != ';')){
      if (header[address] == ' ') {
        token_id++;
        pointer = 0;
        continue;
      }
      tokens[token_id][pointer] = header[address];
      address++;
      pointer++;
    }
  if (strcmp(tokens[0], "port") == 0){
    server_socket[stoh("0"+tokens[1]))] = socket(AF_UNIX, SOCK_STREAM, 0);
    server_addr[stoh("0"+tokens[1])].sun_family = AF_UNIX;
    strcpy(server_addr[stoh("0"+tokens[1])].sun_path, tokens[2]);
    bind(server_socket[stoh("0"+tokens[1])], (struct sockaddr *) &server_addr[stoh("0"+tokens[1])], sizeof(server_addr[stoh("0"+tokens[1])]));
    listen(server_socket[stoh("0"+tokens[1])], 1);
    int clen = sizeof(client_addr);
    client_socket[stoh("0"+tokens[1])] = accept(server_socket, (struct sockaddr *) &client_addr, &clen);
  } else if (strcmp(tokens[0], "?open") == 0){
    if(server_socket[stoh("0"+tokens[1])] == NULL)){
      printf("ERROR: PORT %s IS NOT OPENED\n", tokens[1]));
      exit(0);
    }
  } else if (strcmp(tokens[0], "init") == 0){
    system("~/.local/bin/BoilerRoom/init.sh "+tokens[1]+" "+tokens[2]));
  }
}