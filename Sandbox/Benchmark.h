#pragma once

#include <chrono>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <algorithm>

#define PROFILING 1
#if PROFILING
#define PROFILE_SCOPE(name)	InstrumentationTimer timer##__LINE__(name);
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#endif

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID;
};

struct InstrumentationSession
{
    std::string Name;
};

class Instrumentor
{
public:
    Instrumentor()
            : m_currentSession(nullptr), m_profileCount(0)
    {}

    void BeginSession(const std::string& name, const std::string& filepath = "results.json") {
        m_outputStream.open(filepath);
        WriteHeader();
        m_currentSession = new InstrumentationSession{ name };
    }

    void EndSession() {
        WriteFooter();
        m_outputStream.close();
        delete m_currentSession;
        m_currentSession = nullptr;
        m_profileCount = 0;
    }

    void WriteProfile(const ProfileResult& result) {
        if (m_profileCount++ > 0) {
            m_outputStream << ",";
        }

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_outputStream << "{";
        m_outputStream << "\"cat\":\"function\",";
        m_outputStream << "\"dur\":" << (result.End - result.Start) << ',';
        m_outputStream << "\"name\":\"" << name << "\",";
        m_outputStream << "\"ph\":\"X\",";
        m_outputStream << "\"pid\":0,";
        m_outputStream << "\"tid\":" << result.ThreadID << ",";
        m_outputStream << "\"ts\":" << result.Start;
        m_outputStream << "}";

        m_outputStream.flush();
    }

    void WriteHeader() {
        m_outputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_outputStream.flush();
    }

    void WriteFooter() {
        m_outputStream << "]}";
        m_outputStream.flush();
    }

    static Instrumentor& Get()
    {
        static Instrumentor* instance = new Instrumentor();
        return *instance;
    }

private:
    InstrumentationSession* m_currentSession;
    std::ofstream m_outputStream;
    int m_profileCount;
};

class InstrumentationTimer
{
public:
    InstrumentationTimer(std::string_view name)
            : m_Name(name), m_Stopped(false)
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~InstrumentationTimer()
    {
        if (!m_Stopped) {
            stop();
        }
    }

private:
    void stop() {
        auto end_timepoint = std::chrono::high_resolution_clock::now();
        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Instrumentor::Get().WriteProfile({m_Name, start, end, threadID });

        m_Stopped = true;
    }

private:
    std::string m_Name;
    bool m_Stopped;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};

class Timer
{
public:
    Timer(std::string_view name)
            : m_name(name), m_stopped(false)
    {
        m_start_timepoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        if (!m_stopped) {
            stop();
        }
    }

private:
    void stop() {
        auto end_timepoint = std::chrono::high_resolution_clock::now();
        long long start = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_start_timepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::nanoseconds>(end_timepoint).time_since_epoch().count();

        //std::string res = m_name + ": " + std::to_string(end - start) + "ms\n";
        std::cout << m_name << ": " << (end - start) << "us\n";

        //std::ofstream m_file("C:/Users/user/Desktop/TheLogs/LOGS.txt");
        //m_file << res;
        m_stopped = true;
    }

private:
    std::string m_name;
    bool m_stopped;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_timepoint;
};