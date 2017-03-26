#include <time.h>
#include <limits>

///
/// PROFILE macro for use with perf_counter_t
/// Use like:
/// perf_counter_t pf;
/// PROFILE(pf) { SECTION OF CODE TO PROFILE }
///
#define PROFILE(pf) pf.start(); for( int i = 1; i>0; --i, pf.stop() ) 

class perf_counter_t
{
public:
    /// Constructs a new perf_counter_t.  Stores the current timestamp in the object.
    perf_counter_t();

    /// Resets the minimum, maximum, total, and current times.
    void        reset();

    /// Starts the timer.
    void        start();

    /// Stops the timer and computes the current time, updating the min and max times.
    /// NOTE:  Times are not updated unless perf_counter_t::stop is called!!!
    /// Once a timer is stopped, a subsequent call to perf_counter_t::stop can be made without calling perf_counter_t::start.
    /// This will measure the time since the last perf_counter_t::start.
    void        stop();

    /// Returns the minimum time (in seconds) this counter has recorded.
    double      get_min_time() const                  { return m_time_min; }

    /// Returns the maximum time (in seconds) this counter has recorded.
    double      get_max_time() const                  { return m_time_max; }

    /// Returns the total time (in seconds) this counter has recorded over its lifetime.
    double      get_total_time() const                { return m_time_total; }

    /// Returns the average time (in seconds) this counter has recorded.
    double      get_average_time() const;

    /// Returns the time (in seconds) this counter has last recorded.
    double      get_time() const                     { return m_time_last; }

    /// Returns number of time the perf_counter_t has been start/stopped.
    unsigned long get_count() const                    { return m_num_stops; }

private:
    double m_time_min;
    double m_time_max;
    double m_time_total;
    double m_time_last;
    unsigned long m_num_stops;

    struct timespec m_ts;
};

/*****************************************************************************/
//
// INLINE IMPLEMENTATION
//
/*****************************************************************************/

// perf_counter_t constructor
inline perf_counter_t::perf_counter_t()
{
    reset();
    start();    // fill current timestamp
}


// Reset
inline void perf_counter_t::reset()
{
    m_time_last = m_time_total = m_time_max = 0;
    m_time_min  = std::numeric_limits<double>::max();
    m_num_stops  = 0;
}


inline double perf_counter_t::get_average_time() const
{
    if ( m_num_stops == 0 )  return 0;
    else                     return m_time_total / static_cast<double>(m_num_stops);
}


// Start
inline void perf_counter_t::start()
{
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &m_ts);
}


// Stop
inline void perf_counter_t::stop()
{
    timespec end, diff;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end );

    if ( end.tv_nsec < m_ts.tv_nsec )
    {
        diff.tv_sec = end.tv_sec - m_ts.tv_sec - 1;
        diff.tv_nsec = 1000000000 + end.tv_nsec - m_ts.tv_nsec;
    }
    else
    {
        diff.tv_sec = end.tv_sec - m_ts.tv_sec;
        diff.tv_nsec = end.tv_nsec - m_ts.tv_nsec;
    }


    m_time_last = diff.tv_sec + double(diff.tv_nsec) / 1000000000;

    // Update the various values
    m_time_total += m_time_last;
    if ( m_time_last < m_time_min )    m_time_min = m_time_last;
    if ( m_time_last > m_time_max )    m_time_max = m_time_last;
    ++m_num_stops;
}

