cmake_minimum_required(VERSION 3.31)
project(New_Lab_910)

set(CMAKE_CXX_STANDARD 20)

add_executable(New_Lab_910 main.cpp
        domain/Product.h
        domain/GenericProduct.h
        domain/GenericProduct.cpp
        repository/InMemoryRepository.h
        repository/Repository.h
        repository/InMemoryRepository.cpp
        domain/ProductExceptions.h
        domain/ProductValidators.h
        repository/RepositoryException.h
        domain/ProductTests/GenericProductTests.h
        domain/ProductTests/GenericProductTests.cpp
        repository/RepositoryTests/InMemoryRepositoryTests.h
        repository/RepositoryTests/InMemoryRepositoryTests.cpp
        repository/FileRepository.h
        repository/FileRepository.cpp
        repository/FileRepositoryException.h
        repository/FileRepositoryTests/FIleRepositoryTests.h
        repository/FileRepositoryTests/FileRepositoryTests.cpp
        sevice/VendingMachineService.cpp
        sevice/VendingMachineService.h
        sevice/VendingMachineServiceTests/VMServiceTests.h
        sevice/VendingMachineServiceTests/VMServiceTests.cpp
        controller/VendingMachineController.cpp
        controller/VendingMachineController.h
        controller/VMControllerExceptions.h
        controller/VMControllerTests/VendingMachineControllerTests.h
        controller/VMControllerTests/VendingMachineControllerTests.cpp
        ui/UI.h
        ui/UI.cpp
)
