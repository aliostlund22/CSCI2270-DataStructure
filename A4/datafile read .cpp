bool WordAnalysis::readDataFile(string file)
{
ifstream datafile (file.c_str());
string line;
if ( datafile.is_open())
{
	open = true;
	while(getline(datafile, line))
	{
		string temp;
		stringstream ss(line);
		while(getline(ss, temp, ' '))
		{
			bool added = false;
			if (checkIfCommonWord(temp) == false)
			{
				for(int i = 0; i <= index; i++)
				{
					if( words[i].name == temp)
					{
						words[i].count++;
						added = true;
					}
				}
				if( added == false) 
				{
					words[index].name = temp;
					words[index].count = 1;
					index++;
				}
				if (index == wordCount)
				{
					doubleArrayAndAdd(temp);
				}
			}
			
		
		}
	}
}
else
{
 cout << "Error opening file" <<endl;
}
sortData();
return opened;


}