#pragma once


#define RECORD_STACK_USE_VECTOR

struct RecordStack
{
#if defined(RECORD_STACK_USE_VECTOR)
    using Container = std::vector<Record>;
#else
    using Container = std::stack<Record>;
#endif

    using container_type   = Container                          ;
    using value_type       = typename Container::value_type     ;
    using size_type        = typename Container::size_type      ;
    using reference        = typename Container::reference      ;
    using const_reference  = typename Container::const_reference;

#if defined(RECORD_STACK_USE_VECTOR)

    bool empty() const                   { return m_stack.empty();}
    size_type size() const               { return m_stack.size(); }
	
    void push( const value_type& value ) { m_stack.emplace_back(value); }
    void push( value_type&& value )      { m_stack.emplace_back(std::forward<value_type>(value)); }
    void pop()                           { m_stack.pop_back(); }

    void clear()                         { m_stack.clear(); }

    reference top()                      { return m_stack.back(); }
    const_reference top() const          { return m_stack.back(); }

#else

    bool empty() const                   { return m_stack.empty();}
    size_type size() const               { return m_stack.size(); }
	
    void push( const value_type& value ) { m_stack.push(value); }
    void push( value_type&& value )      { m_stack.push(std::forward<value_type>(value)); }
    void pop()                           { m_stack.pop(); }

    void clear()                         { while(!empty()) pop(); }

    reference top()                      { return m_stack.top();  }
    const_reference top() const          { return m_stack.top();  }

    // reference top(int idx)
    // {
    //  
    //     return m_stack.top();
    // }
    //  
    // const_reference top() const
    // {
    //     return m_stack.top();
    // }


#endif

	

protected:

    Container m_stack;

}; // struct RecordStack


