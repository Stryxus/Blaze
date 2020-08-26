#include "pch.h"

#include "Blaze.NET.h"

using namespace System;
using namespace System::Net;
using namespace System::Runtime::InteropServices;

using namespace NUglify;
using namespace NUglify::Css;
using namespace NUglify::JavaScript;
using namespace NUglify::Helpers;

using namespace FFMpegCore;
using namespace FFMpegCore::Arguments;
using namespace FFMpegCore::Enums;
using namespace FFMpegCore::Exceptions;
using namespace FFMpegCore::Extend;
using namespace FFMpegCore::Helpers;
using namespace FFMpegCore::Pipes;

//

string minify_css(string& content)
{
	CssSettings^ css_settings = gcnew CssSettings();
	String^ source = gcnew String(content.c_str());

	css_settings->CommentMode = CssComment::None;
	css_settings->OutputMode = OutputMode::SingleLine;

	UglifyResult result = Uglify::Css(source, css_settings, nullptr);

	string rstr;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(result.Code)).ToPointer();
	rstr = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return rstr;
}

string minify_js(string& content)
{
	CodeSettings^ code_settings = gcnew CodeSettings();
	String^ source = gcnew String(content.c_str());

	code_settings->AmdSupport = false;
	code_settings->Format = JavaScriptFormat::Normal;
	code_settings->OutputMode = OutputMode::SingleLine;
	code_settings->PreserveImportantComments = false;
	code_settings->MinifyCode = true;
	code_settings->RemoveUnneededCode = false;

	UglifyResult result = Uglify::Js(source, code_settings);

	string rstr;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(result.Code)).ToPointer();
	rstr = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return rstr;
}

//

string convert_video_to_webm(string& input_path, string& output_path, int bitrate)
{
	String^ in_path = gcnew String(input_path.c_str());
	String^ out_path = gcnew String(output_path.c_str());
	MediaAnalysis^ probe = FFProbe::Analyse(in_path, int::MaxValue);

	FFMpegArguments^ args = gcnew FFMpegArguments();
	args->FromInputFiles(in_path);
	args->WithVideoCodec(VideoCodec::LibVpx);
	args->WithAudioCodec(AudioCodec::LibFdk_Aac);
	args->WithVariableBitrate(bitrate);
	args->WithAudioBitrate(256);
	args->UsingThreads(8);
	args->WithSpeedPreset(Speed::VerySlow);
	args->UsingMultithreading(true);
	args->WithFastStart();
	args->Scale(VideoSize::Original);
	FFMpegArgumentProcessor^ processor = args->OutputToFile(out_path, true);
	processor->ProcessSynchronously(false);
}

//

string download_data(string& link)
{
	WebClient^ client = gcnew WebClient();
	string rstr;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(client->DownloadString(gcnew String(link.c_str())))).ToPointer();
	rstr = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return rstr;
}