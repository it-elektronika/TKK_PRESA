int main()
{
  program = 1;
  init();
  initVars(); 
  /*ctx = modbus_new_tcp("192.168.1.78", 1500);
  if(modbus_connect(ctx) == -1) 
  {
    fprintf(stderr,"Connection failed: %s\n",modbus_strerror(errno));
    modbus_free(ctx);
    exit(101);
  }
  nb = sizeof(regs)/sizeof(int16_t);   
  modbus_set_debug(ctx, FALSE);
 */
  while(program == 1)
  {
    /*rc = modbus_read_registers(ctx, 1, nb, regs);
    for(i = 0; i < 10; i++)
    {
      printf("REG%d:%d\n", i, regs[i]);
    }
    usleep(1000);
    errorCheck();*/
    touchUpdate();
    renderBackground();
    if(page!=4)
    {
      renderStatusBar();
    }
    renderContent();
    SDL_RenderPresent(renderer);
  }
  return 0;
}
