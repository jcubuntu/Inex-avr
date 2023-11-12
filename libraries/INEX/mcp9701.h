//============== Read Temperature with MCP9701 ================//
int read_temp(int ch)
{
	float temp;
	int val=0;
	for(int i=0;i<20;i++)
	{
		val += analog(ch);
	}
	val = val/20;
	temp = (float(val*0.25))-20.51;
    return((int)temp);	
}
float read_temp_float(int ch)
{
	float temp;
	int val=0;
	for(int i=0;i<20;i++)
	{
		val += analog(ch);
	}
	val = val/20;
	temp = (float(val*0.25))-20.51;
    return(temp);	
}