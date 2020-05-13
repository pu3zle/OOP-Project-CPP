//DynamicArray
#pragma once

namespace pzl
{
	using size_type = unsigned int;

	template <typename TElem>
	class DynamicArray
	{
	private:
		size_type m_size;
		size_type m_length;
		char* m_elements;

	public:

		class iterator {
		private:
			const DynamicArray<TElem>* m_parent;
		public:
			TElem* m_current;
			size_type m_position;

			iterator() noexcept
				:m_parent(nullptr)
				, m_current(nullptr)
				, m_position(0)
			{}
			iterator(const typename DynamicArray<TElem>* elem)
				:m_parent(elem)
				, m_current(reinterpret_cast<TElem*>(m_parent->m_elements))
				, m_position(0)
			{}
			iterator(const DynamicArray<TElem>::iterator& elem) noexcept
				:m_parent(elem.m_parent)
				, m_current(elem.m_current)
				, m_position(elem.m_position)
			{}
			iterator& operator=(const DynamicArray<TElem>::iterator& elem) noexcept
			{
				this->m_parent = elem.m_parent;
				this->m_current = elem.m_current;
				this->m_position = elem.m_position;
				return *this;
			}

			//prefix ++ overload
			iterator& operator++() noexcept
			{
				if (m_current == nullptr)
					return *this;
				if (m_position < m_parent->m_length)
				{
					m_position++;
				}
				return *this;
			}

			// Postfix ++ overload 
			iterator operator++(int) noexcept
			{
				iterator it = *this;
				++* this;
				return it;
			}

			//prefix -- overload
			iterator& operator--() noexcept
			{
				if (m_current == nullptr)
					return *this;
				if (m_position > 0)
				{
					m_position--;
				}
				return *this;
			}

			// Postfix -- overload 
			iterator operator--(int) noexcept
			{
				iterator it = *this;
				--* this;
				return it;
			}

			iterator operator-(const iterator& it)
			{
				iterator out;
				if (it.m_parent != this->m_parent || it.m_current != this->m_current)
				{
					throw std::string("error");
				}
				out.m_parent = m_parent;
				out.m_current = m_current;
				out.m_position = this->m_position - it.m_position;
				return out;
			}

			const iterator operator+(const int offset)
			{
				iterator out(*this);
				out.m_position += offset;
				return out;
			}

			bool operator==(const iterator& other) const noexcept {
				return (m_parent == other.m_parent && 
						m_current == other.m_current && 
						m_position == other.m_position);
			}

			void set_position(size_type pos) noexcept
			{
				m_position = pos;
			}

			bool operator!=(const iterator& it) noexcept
			{
				return (m_parent != it.m_parent) ||
					(m_parent == it.m_parent && m_current != it.m_current) ||
					(m_parent == it.m_parent && m_current == it.m_current && m_position != it.m_position);
			}

			TElem& operator*()
			{
				if (m_position > m_parent->m_length)
					throw std::string("error");
				return *(m_current + m_position);
			}

			TElem* current()
			{
				if (m_position > m_parent->m_length)
					throw std::string("error");
				return (m_current + m_position);
			}

		};

		DynamicArray()
			: m_size(2)
			, m_length(0)
			, m_elements(new char[sizeof(TElem) * m_size])
		{}
		DynamicArray(size_type size)
			: m_size(size)
			, m_length(0)
			, m_elements(new char[sizeof(TElem) * m_size])
		{}
		DynamicArray(const DynamicArray& DA)
			:m_size(DA.m_size)
			, m_length(DA.m_length)
			, m_elements(new char[sizeof(TElem) * m_size])
		{
			for (size_type i = 0; i < m_length; i++)
			{
				//placement new to copy the elements from source into the current vector.
				new(m_elements + sizeof(TElem) * i)TElem(DA[i]);
			}
		}
		DynamicArray& operator=(const DynamicArray& other)
		{
			DynamicArray temp(*this);
			swap(other);
			return *this;
		}
		~DynamicArray()
		{
			this->clear();
			delete[] m_elements;
			m_size = 0;
			m_length = 0;
		}


		void swap(const DynamicArray& other)
		{
			if (*this == other)
				return;

			this->m_size = other.m_size;
			size_type tmp_length = other.m_length;

			this->clear();
			delete[] m_elements;

			this->m_elements = new char[sizeof(TElem) * other.m_size];
			this->m_length = tmp_length;

			for (size_type i = 0; i < other.m_length; i++)
			{
				new(m_elements + sizeof(TElem) * i)TElem(other[i]);
			}
		}

		bool operator==(const DynamicArray& other)
		{
			return m_elements == other.m_elements;
		}

		template <typename U>
		friend std::ostream& operator<<(std::ostream& os, const DynamicArray<U>& da);

		//utilities
		void resize(size_type new_size)
		{
			char* buffer = new char[sizeof(TElem) * new_size];

			for (size_type i = 0; i < m_length; i++)
			{
				new(buffer + sizeof(TElem) * i)TElem((reinterpret_cast<TElem*>(this->m_elements))[i]);
			}

			m_size = new_size;
			size_type tmp = m_length;

			this->clear();
			delete[] m_elements;

			m_elements = buffer;
			m_length = tmp;
		}

		//adding
		void push_back(const TElem& elem)
		{
			if (this->m_length == this->m_size)
				resize(2 * m_size);
			new(m_elements + m_length * sizeof(TElem))TElem(elem);
			m_length++;
		}

		//read
		TElem& operator[](size_type pos)
		{
			if (pos > m_length)
				throw std::string("error");
			return (reinterpret_cast<TElem*>(m_elements))[pos];
		}

		TElem& operator[](const iterator& it)
		{
			if(it.m_position > m_length)
				throw std::string("error");
			return (reinterpret_cast<TElem*>(m_elements))[it.m_position];
		}

		const TElem& operator[](size_type pos) const
		{
			if (pos > m_length)
				throw std::string("error");
			return (reinterpret_cast<TElem*>(m_elements))[pos];
		}

		const TElem& at(size_type pos) const
		{
			if (pos > m_length)
				throw std::string("error");
			return (reinterpret_cast<TElem*>(m_elements))[pos];
		}

		TElem& at(size_type pos)
		{
			if (pos > m_length)
				throw std::string("error");
			return (reinterpret_cast<TElem*>(m_elements))[pos];
		}

		TElem& at(const iterator& it)
		{
			if (it.m_position > m_length)
				throw std::string("error");
			return (reinterpret_cast<TElem*>(m_elements))[it.m_position];
		}

		const size_type& size() const {
			return m_length;
		}

		const bool empty() const
		{
			return m_length == 0;
		}
		const size_type capacity() const {
			return m_size;
		}

		iterator begin() const {
			return iterator(this);
		}

		iterator end() const {
			iterator it(this);
			it.set_position(this->m_length);
			return it;
		}

		//delete
		void pop_back()
		{
			if (m_length == 0)
				throw std::string("error");

			//call the destructor of the element removed
			(reinterpret_cast<TElem*>(m_elements)[m_length - 1]).~TElem();
			m_length--;

			if (m_length * 4 < m_size && m_length != 0)
			{
				this->resize(m_size / 2);
				m_size /= 2;
			}
		}
		void erase(iterator it)
		{
			if (it.m_position >= m_length)
				throw std::string("error");

			TElem* tmp = reinterpret_cast<TElem*>(m_elements);
			tmp[it.m_position].~TElem();

			for (size_type i = it.m_position; i < m_length - 1; i++)
			{
				tmp[i] = tmp[i + 1];
			}
			m_length--;

			if (m_length * 4 < m_size && m_length != 0)
			{
				this->resize(m_size / 2);
				m_size /= 2;
			}
		}
		void clear()
		{
			for (size_type i = 0; i < m_length; i++)
				(reinterpret_cast<TElem*>(m_elements)[i]).~TElem();
			m_length = 0;
		}

	};

	template <typename TElem>
	std::ostream& operator<<(std::ostream& os, const DynamicArray<TElem>& da)
	{
		for (size_type i = 0; i < da.size(); i++)
		{
			os << da.at(i) << " ";
		}
		os << "\n";
		return os;
	}

}
