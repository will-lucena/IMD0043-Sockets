    clientConn = accept(sd, (struct sockaddr*)NULL, NULL);

    /* INICIA O BUFFER DE COMUNICACAO */
    memset(msg, 0x0, MAX_MSG);

    //Hora
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t tt;
    tt = std::chrono::system_clock::to_time_t ( today );

    // imprimindo mensagem recebida
    snprintf(msg, sizeof(msg), "%.24s\r\n", ctime(&tt)); 

    write(clientConn, msg, strlen(msg));
 
    close(clientConn);
    
    sleep(1);