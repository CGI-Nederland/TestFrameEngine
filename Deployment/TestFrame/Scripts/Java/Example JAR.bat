set inifile="C:\TestFrame\engine.ini"
set clusterfile="C:\TestFrame\Cluster\Example.txt"
set reportfile="C:\TestFrame\Report\ExampleReport.rtf"

java -cp "C:\TestFrame\Scripts\Java\TestFrame.jar" TestFrame %inifile% %clusterfile% %reportfile%
