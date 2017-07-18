# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
# For documentation see https://www.vagrantup.com/docs/vagrantfile/
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  # All Vagrant configuration is done here. The most common configuration
  # options are documented and commented below. For a complete reference,
  # please see the online documentation at vagrantup.com.

  # use the CERN VM as a starting point (Scientific Linux 6)
  config.vm.box = 'cernvm/3-prod'

  # forward ports
  # config.vm.network :forwarded_port, guest: 8060, host: 8060

  # x-window forwarding (unix-only)
  config.ssh.forward_x11 = true

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  config.vm.synced_folder ".", "/vagrant", nfs: false

  # if you have an existing vagrant box after this was added in, please run `vagrant provision`
  # after `vagrant up`.
  # add your git config to the vagrant box
  #config.vm.provision "file", source: "~/.gitconfig", destination: "/home/vagrant/.gitconfig"

  # example of executing commands when provisioning the machine
  config.vm.provision "shell", inline: <<-SHELL
        sudo mkdir /software
        sudo chown vagrant /software
  SHELL

  config.vm.provider "virtualbox" do |vb|
    # Display the VirtualBox GUI when booting the machine
    vb.gui = false
    vb.memory = "2048"
    vb.cpus = 2
  end
end
