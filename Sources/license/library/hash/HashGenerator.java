// This program can be used to generate random number for hash algorithms
// Wilco Schillemans

import java.util.Random;

class HashGenerator
{
	static public void main(String args[])
	{
		Random myGenerator = new Random();
		int x = 26;
		int y = 140;
		
		for (int i = 0; i < (x * y); i++)
		{
			if (i == 0)
			{ 
				System.out.println("\t{");
				System.out.println("\t\t// Position " + (i/x + 1));
				System.out.print("\t\t\t");
			}
			else if (i%x == 0)
			{
				System.out.println(",");
				System.out.println("");
				System.out.println("\t\t// Position " + (i/x + 1));
				System.out.print("\t\t\t");
			}
			else if (i%13 == 0)
			{
				System.out.println(", ");
				System.out.print("\t\t\t");
			}
			else
			{ System.out.print(", "); }

			System.out.print("0x" + Integer.toHexString(myGenerator.nextInt()&0x0000ffff));
		}

		System.out.println("");
		System.out.println("\t};");
	}
}
