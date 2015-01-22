/*****************************************************************************
 * $Workfile: $
 * $Revision: $
 * $Modtime	: $
 * $Author	: $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000-2007 LogicaCMG NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

import TestFrame.Engine;

/**
 * TestFrame Java example. This example demonstrates the Java interface for 
 * TestFrame Engine 6. 
 *
 * @author	<a href=mailto:Engine5@logicacmg.nl>Engine Team</a>
 * @version	$Revision: $ $Modtime: $
 */
class TestFrame
{
	public static void main(String[] args)
	{
		String strIniFile =     new String("");
		String strClusterName = new String("");
		String strReportName =  new String("");
		
		// Get the command line arguments
		try
		{
			strIniFile     = args[0];
			strClusterName = args[1];
			strReportName  = args[2];
		}
		catch (ArrayIndexOutOfBoundsException e)
		{ /* StartEngine will handle argument checking */ }
		
		// Echo the arguments for clarity		
		System.out.println("LogicaCMG TestFrame engine java example\n");
		System.out.println("Inifile name: " + strIniFile);
		System.out.println("Cluster name: " + strClusterName);
		System.out.println("Report name:  " + strReportName);
		
		// Register our action words
		Engine.RegisterActionWord("print some numbers", "PrintSomeNumbers");
		Engine.RegisterActionWord("perform a check", "PerformACheck");
		Engine.RegisterActionWord("print an error", "PrintAnError");

		// Start the engine
		if (Engine.StartEngine(strClusterName, strReportName, strIniFile) == 1)
		{
			// Process each test line until none are left
			while (Engine.ProcessNextLine() != 0) 
			{ 	
				String strActionWordFunction = Engine.GetActionWordFunction();
				
				if      (strActionWordFunction.equals("PrintSomeNumbers"))
				{ 
					PrintSomeNumbers();
				}
				else if (strActionWordFunction.equals("PerformACheck"))
				{ 
					PerformACheck();
			 	}
				else if (strActionWordFunction.equals("PrintAnError"))
				{ 
					PrintAnError(); 
				}
				else
				{
					// Error: unknown actionword
					Engine.StopEngine();
				}
			}

			// Stop the engine and generate the report
			Engine.StopEngine();
			Engine.GenerateReport();
		}
		else
		{
			// Engine could not be started
			System.out.println("\nError: Engine could not be started. (For more information see the file 'error.log')");
		}
	}

	public static void PrintSomeNumbers()
	{
		// Just report the parameters as comment
		Engine.ReportComment(Engine.GetParameter(1));
		Engine.ReportComment(Engine.GetParameter(2));
		Engine.ReportComment(Engine.GetParameter(3));
	}

	public static void PerformACheck()
	{
		// Compare parameter 1 and 2
		Engine.CheckParameter(1, Engine.GetParameter(2));
	}
	
	public static void PrintAnError()
	{
		// Report the parameter as an error
		Engine.ReportError(Engine.GetParameter(1), Engine.TFE_ERROR);
	}
}