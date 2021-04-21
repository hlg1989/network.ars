#ifndef RL_ELEMTYPE_CIRCLEDATASET_HPP
#define RL_ELEMTYPE_CIRCLEDATASET_HPP

#include <stdint.h>
#include <math.h>

namespace RL {
namespace ElemType {
	template <typename T>
	class CircleDataSet {
	public:
		CircleDataSet()
			: m_uidata(0)
			, m_undata(0)
			, m_uMaxDataSize(0)
			, T_data(nullptr)
		{

		}
		CircleDataSet(uint32_t uMaxDataSize)
			: m_uidata(0)
			, m_undata(0)
		{
			T_data = new T[uMaxDataSize];
			memset(T_data, 0, sizeof(T_data));
			m_uMaxDataSize = uMaxDataSize;
		}
		~CircleDataSet() {
			if (T_data) {
				delete[] T_data;
				T_data = nullptr;
			}
		}
		void Resize(uint32_t uMaxDataSize) {
			if (T_data) {
				delete[] T_data;
				T_data = nullptr;
			}
			T_data = new T[uMaxDataSize];
			memset(T_data, 0, sizeof(T_data));
			m_uMaxDataSize = uMaxDataSize;
		}
		void Append(T Tdata) {
			if (m_uidata >= m_uMaxDataSize) {
				return;
			}

			T_data[m_uidata] = Tdata;
			m_undata = ++m_undata > m_uMaxDataSize ? m_uMaxDataSize : m_undata;
			m_uidata = ++m_uidata % m_uMaxDataSize;
		}
		T Min() {
			if (m_undata <= 0) {
				return nanf("inf");
			}
			T mindata = T_data[0];
			for (int i = 0; i < m_undata; i++) {
				mindata = mindata < T_data[i] ? mindata : T_data[i];
			}
			return mindata;
		}
		T Max() {
			if (m_undata <= 0) {
				return nanf("-inf");
			}
			T maxdata = T_data[0];
			for (int i = 0; i < m_undata; i++) {
				maxdata = maxdata > T_data[i] ? maxdata : T_data[i];
			}
			return maxdata;
		}
		double Avg() {
			if (m_undata <= 0) {
				return nanf("inf");
			}
			double avg = static_cast<double>(T_data[0]);

			double diff = 0.0;
			for (int i = 0; i < m_undata; i++) {
				diff += static_cast<double>(T_data[i]) - avg;
			}
			avg += diff / m_undata;
		}
		double Var() {
			if (m_undata <= 0) {
				return nanf("inf");
			}
			double avg = Avg();
			double var = 0;
			if (m_undata > 1) {
				for (int i = 0; i < m_undata; i++) {
					var += (avg - static_cast<double>(T_data[i]))*(avg - static_cast<double>(T_data[i])) / (m_undata - 1);
				}
				var = sqrtf(var);
			}
			return var;
		}
		uint32_t Size() {
			return m_undata;
		}

	private:
		T *T_data;
		uint32_t m_uidata;
		uint32_t m_undata;
		uint32_t m_uMaxDataSize;
	};
}
}//namespace RL
#endif
