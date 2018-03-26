const execSync = require('child_process').execSync;

for(var i = 1; i < 16; i++)
{
	for(var j = 0; j < 16; j++)
	{
		for(var k = 0; k < 16; k++)
		{
			var nonce = get_hex(i) + get_hex(j) + get_hex(k); 
			var code = execSync('./human4b --bin ' + nonce + '7DDBFC09F0 >> bigstream.bin');
		}
	}
}


function get_hex(num)
{
	switch(num)
	{
		case 10:
			return 'A';
		case 11:
			return 'B';
		case 12:
			return 'C';
		case 13:
			return 'D';
		case 14:
			return 'E';
		case 15:
			return 'F';
		default:
			return num.toString();
	}
}
