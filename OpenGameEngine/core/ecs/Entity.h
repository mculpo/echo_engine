#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <cstdint>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Component.h"
namespace openge {
	template<typename T>
	class Entity
	{
	private:
		std::uint64_t  m_id;
		/*
		*
		* O std::unordered_map é uma classe de contêiner da biblioteca padrão do C++ que implementa uma tabela de hash. Ele armazena elementos em pares chave-valor, onde cada chave é única e mapeada para um valor correspondente. A principal característica do std::unordered_map é que ele fornece um acesso rápido aos elementos com base em suas chaves, em tempo constante (O(1)) na média.
		*
		* Em programação, um "wrapper" é uma classe ou estrutura que encapsula ou "embrulha" outro objeto ou tipo de dados, fornecendo uma interface mais conveniente ou modificando o comportamento do objeto subjacente.

		No caso específico de std::type_index, é um wrapper para std::type_info. O std::type_info é um tipo que fornece informações sobre um tipo em tempo de execução, como seu nome e outras características. No entanto, std::type_info não pode ser usado diretamente como uma chave em contêineres como unordered_map, pois não suporta comparação adequada por igualdade.

		O std::type_index atua como um wrapper para std::type_info, fornecendo operadores de comparação e hash necessários para ser usado como uma chave em contêineres, como unordered_map. Ele encapsula o std::type_info e fornece uma interface mais conveniente para comparar tipos.

		Assim, o std::type_index permite que os tipos sejam usados como chaves em contêineres, como unordered_map, ao fornecer uma comparação adequada e funcionalidades de hash para esses tipos de dados.
		*/
		std::unordered_map<std::type_index, std::shared_ptr<Component<T>>> m_components;
	public:
		Entity();
		Entity(std::uint64_t id);
		~Entity();

		// add a component to an Entity
		template<typename ComponentType, typename... Args>
		void addComponent(Args&&... args);

		// get a component to an Entity
		template<typename ComponentType>
		std::shared_ptr<ComponentType> getComponent();

		// verify if exist a component to an Entity
		template<typename ComponentType>
		bool HasComponent();

		// remove a component to an Entity
		template<typename ComponentType>
		void removeComponent();
	};
}
#endif

