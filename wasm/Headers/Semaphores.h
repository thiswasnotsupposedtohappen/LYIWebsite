void  LockBlocking(volatile uint32* lock,uint8 processorid)
{
    while(1)
    {
        if(*lock == 0 || *lock == processorid)
        {
            *lock = processorid;
            if(*lock == processorid)
                break;
        }
    }
}
uint8 LockNonBlocking(volatile uint32* lock,uint8 processorid)
{
    if(*lock == 0 || *lock == processorid)
    {
        *lock = processorid;
        if(*lock == processorid)
            return 1;
    }
    return 0;
}
void  Unlock(volatile uint32* lock,uint8 processorid)
{
    if(*lock == processorid)
    {
        *lock = 0;
    }
}
