TestFrame
=========

Testframe engine of CGI

# Visual Studo 2013

Download and install the Visual Studio 2013 Community Edition

Download extra library for multibyte support:

[Multibyte MFC Library for Visual Studio 2013](http://www.microsoft.com/en-us/download/details.aspx?id=40770)


# Tips

## SDF and IPCH files

You can safely delete the .sdf file and ipch folder but you can also stop VS from putting those files in the project folder in the first place. (Useful if you have your source in a SVN or other synchronised folder, or if you store your project on a small volume like a USB stick or SSD and you don't want those large files stored in the same folder)

Go to Tools -> Options -> Text Editor -> C/C++ -> Advanced

In the "Fallback Location", set "Always Use Fallback Location" to True and "Do Not Warn If Fallback Location Used" to True. In "Fallback Location" you can either put a path like C:\Temp or if you leave it blank then VS will use the temporary directory in your AppData folder.