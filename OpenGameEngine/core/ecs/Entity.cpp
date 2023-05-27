#include "Entity.h"
namespace openge {
	// Construtor padrão
	template<typename T>
	Entity<T>::Entity() : m_id(0) {}

	// Construtor com parâmetros
	template<typename T>
	Entity<T>::Entity(std::uint64_t entityId) : m_id(entityId) {}

	// Destrutor
	template<typename T>
	Entity<T>::~Entity() {}
	/*
	* static_assert é uma diretiva de pré-processador que permite realizar verificação estática de uma expressão em tempo de compilação.
	* É usada para impor uma condição em tempo de compilação e gerar um erro de compilação se a condição não for satisfeita.
	*/
	template<typename T>
	template<typename ComponentType, typename ...Args>
	void Entity<T>::addComponent(Args && ...args)
	{
		static_assert(std::is_same<ComponentType, Component<T>>::value, "ComponentType must be Component<T>");
		/*
		std::forward<Args>(args)... é uma construção usada para encaminhar os argumentos passados para a função make_shared para o construtor do ComponentType. Ela é usada para preservar a categoria de valor (lvalue ou rvalue) dos argumentos passados para o make_shared.

		Args é um pacote de argumentos que pode conter zero ou mais argumentos. É uma forma genérica de especificar os argumentos do construtor.

		std::forward é uma função de utilidade que permite encaminhar argumentos exatamente como foram passados para uma função.
		*/
		std::shared_ptr<ComponentType> component = std::make_shared<ComponentType>(std::forward<Args>(args)...);
		/*
		A função typeid é uma operação do C++ que retorna um objeto do tipo std::type_info, que contém informações sobre o tipo em tempo de execução de um objeto ou uma expressão.

		O typeid é usado para obter informações sobre tipos em tempo de execução. Ele pode ser útil em situações em que é necessário realizar verificações ou tomar decisões com base no tipo de objeto em tempo de execução.
		*/
		m_components[std::type_index(typeid(ComponentType))] = component;
	}

	template<typename T>
	template<typename ComponentType>
	std::shared_ptr<ComponentType> Entity<T>::getComponent()
	{
		static_assert(std::is_same<ComponentType, Component<T>>::value, "ComponentType must be Component<T>");
		auto it = m_components.find(std::type_index(typeid(ComponentType)));
		if (it != m_components.end()) {
			/**
			* std::dynamic_pointer_cast é uma função da biblioteca padrão do C++ que permite realizar conversões seguras de ponteiros inteligentes (std::shared_ptr ou std::weak_ptr) para outros tipos relacionados.
			*
			* A chave e o valor do par usando it->first e it->second, respectivamente.
			*/
			return std::dynamic_pointer_cast<ComponentType>(it->second);
		}
		return nullptr;
	}

	template<typename T>
	template<typename ComponentType>
	bool Entity<T>::HasComponent()
	{
		static_assert(std::is_same<ComponentType, Component<T>>::value, "ComponentType must be Component<T>");
		return m_components.find(std::type_index(typeid(ComponentType))) != !m_components.end();
	}

	template<typename T>
	template<typename ComponentType>
	void Entity<T>::removeComponent()
	{
		static_assert(std::is_same<ComponentType, Component<T>>::value, "ComponentType must be Component<T>");
		m_components.erase(std::type_index(typeid(ComponentType)));
	}
}
